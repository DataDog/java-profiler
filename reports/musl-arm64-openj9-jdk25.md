---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-28 12:52:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777394793 64
1777394798 64
1777394803 64
1777394808 64
1777394813 64
1777394818 64
1777394823 64
1777394828 64
1777394833 64
1777394838 64
1777394843 64
1777394848 64
1777394853 64
1777394858 64
1777394863 64
1777394868 64
1777394874 64
1777394879 64
1777394884 64
1777394889 64
```
</details>

---

