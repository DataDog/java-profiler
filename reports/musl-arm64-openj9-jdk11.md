---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:28:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795641778 33
1795641783 33
1795641788 33
1795641793 33
1795641798 33
1795641803 33
1795641808 33
1795641813 33
1795641818 33
1795641823 33
1795641828 33
1795641833 33
1795641838 33
1795641843 64
1795641848 64
1795641853 64
1795641858 64
1795641863 64
1795641868 64
1795641873 64
```
</details>

---

