---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:36:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 13 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795631515 47
1795631520 47
1795631525 47
1795631530 47
1795631535 47
1795631540 47
1795631545 47
1795631550 47
1795631555 47
1795631560 47
1795631565 47
1795631570 47
1795631575 47
1795631580 47
1795631585 47
1795631590 47
1795631595 47
1795631600 47
1795631605 47
1795631610 47
```
</details>

---

