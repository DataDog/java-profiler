---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 11:09:35 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 62-96 cores)</summary>

```
1790262022 96
1790262027 96
1790262032 96
1790262037 96
1790262042 96
1790262047 96
1790262052 96
1790262057 96
1790262062 96
1790262067 66
1790262072 66
1790262077 66
1790262082 66
1790262087 66
1790262092 66
1790262097 66
1790262102 66
1790262107 66
1790262112 64
1790262117 64
```
</details>

---

