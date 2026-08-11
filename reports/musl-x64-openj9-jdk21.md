---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 04:47:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 93-96 cores)</summary>

```
1786437788 93
1786437793 93
1786437798 93
1786437803 93
1786437808 93
1786437813 93
1786437818 93
1786437823 93
1786437828 93
1786437833 96
1786437838 96
1786437843 96
1786437848 96
1786437853 96
1786437858 96
1786437864 96
1786437869 96
1786437874 96
1786437879 96
1786437884 96
```
</details>

---

