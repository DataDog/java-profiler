---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 09:34:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 74-87 cores)</summary>

```
1795011943 74
1795011948 74
1795011953 74
1795011958 74
1795011963 74
1795011968 74
1795011973 74
1795011978 74
1795011983 76
1795011988 76
1795011993 76
1795011998 76
1795012003 76
1795012008 85
1795012013 85
1795012018 85
1795012023 85
1795012028 85
1795012033 85
1795012038 85
```
</details>

---

