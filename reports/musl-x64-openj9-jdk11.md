---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:33:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (3 unique values: 78-93 cores)</summary>

```
1795631256 93
1795631261 93
1795631266 93
1795631271 93
1795631276 93
1795631281 84
1795631286 84
1795631291 84
1795631296 84
1795631301 84
1795631306 84
1795631311 84
1795631316 84
1795631321 84
1795631326 84
1795631331 84
1795631336 84
1795631341 84
1795631347 84
1795631352 84
```
</details>

---

