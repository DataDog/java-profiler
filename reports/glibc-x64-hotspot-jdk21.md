---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:49:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 35-63 cores)</summary>

```
1795621586 35
1795621591 35
1795621596 35
1795621601 35
1795621606 35
1795621611 35
1795621616 35
1795621621 35
1795621626 35
1795621631 35
1795621636 35
1795621641 35
1795621646 35
1795621651 35
1795621656 35
1795621661 35
1795621666 35
1795621671 35
1795621676 63
1795621681 63
```
</details>

---

