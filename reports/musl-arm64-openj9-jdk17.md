---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-06 13:09:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 14 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1791306169 48
1791306174 48
1791306179 48
1791306184 48
1791306189 48
1791306194 48
1791306199 48
1791306204 45
1791306209 45
1791306214 45
1791306219 45
1791306224 45
1791306229 45
1791306234 45
1791306239 45
1791306244 45
1791306249 45
1791306254 46
1791306259 46
1791306264 46
```
</details>

---

