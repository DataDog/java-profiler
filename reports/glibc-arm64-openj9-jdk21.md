---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:48:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 24-33 cores)</summary>

```
1795632235 33
1795632240 33
1795632245 33
1795632250 33
1795632255 33
1795632260 33
1795632265 33
1795632270 33
1795632275 33
1795632280 33
1795632285 33
1795632290 33
1795632295 33
1795632300 33
1795632305 33
1795632310 33
1795632315 29
1795632320 29
1795632325 29
1795632330 29
```
</details>

---

