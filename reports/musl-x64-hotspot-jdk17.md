---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:33:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
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
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 87-91 cores)</summary>

```
1795631239 89
1795631244 89
1795631249 89
1795631254 89
1795631259 89
1795631264 89
1795631269 89
1795631274 89
1795631279 89
1795631284 89
1795631289 89
1795631294 89
1795631299 87
1795631304 87
1795631309 87
1795631314 87
1795631319 87
1795631324 87
1795631329 87
1795631334 87
```
</details>

---

