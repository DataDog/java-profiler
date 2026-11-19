---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:13:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795097252 50
1795097257 50
1795097262 50
1795097267 50
1795097272 50
1795097277 50
1795097282 50
1795097287 50
1795097292 50
1795097297 50
1795097302 50
1795097307 50
1795097312 50
1795097317 50
1795097322 50
1795097327 50
1795097332 50
1795097337 50
1795097342 50
1795097347 50
```
</details>

---

