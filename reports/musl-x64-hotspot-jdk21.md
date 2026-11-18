---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:10:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1795010697 44
1795010702 44
1795010707 44
1795010712 44
1795010717 44
1795010722 44
1795010727 44
1795010732 44
1795010737 44
1795010742 44
1795010747 44
1795010752 44
1795010757 44
1795010762 48
1795010767 48
1795010772 48
1795010777 48
1795010782 48
1795010787 48
1795010792 48
```
</details>

---

