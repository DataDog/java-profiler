---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 11:40:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 299 |
| Sample Rate | 4.98/sec |
| Health Score | 311% |
| Threads | 11 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 44-59 cores)</summary>

```
1795192551 44
1795192556 44
1795192561 44
1795192566 44
1795192571 44
1795192576 44
1795192581 44
1795192586 44
1795192591 44
1795192596 44
1795192601 44
1795192606 59
1795192611 59
1795192616 59
1795192621 59
1795192626 59
1795192631 59
1795192636 59
1795192641 59
1795192646 59
```
</details>

---

