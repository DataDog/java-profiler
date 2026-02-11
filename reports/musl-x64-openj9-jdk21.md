---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:59:20 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 11 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1147 |
| Sample Rate | 19.12/sec |
| Health Score | 1195% |
| Threads | 14 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (3 unique values: 79-84 cores)</summary>

```
1770828868 83
1770828873 83
1770828878 83
1770828883 83
1770828888 83
1770828893 83
1770828898 83
1770828903 83
1770828908 84
1770828913 84
1770828918 84
1770828923 84
1770828928 84
1770828933 79
1770828938 79
1770828943 79
1770828948 79
1770828953 79
1770828958 79
1770828963 79
```
</details>

---

