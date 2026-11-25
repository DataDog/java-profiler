---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1795626765 64
1795626770 64
1795626775 64
1795626780 64
1795626785 64
1795626790 64
1795626795 64
1795626800 64
1795626805 64
1795626810 64
1795626815 64
1795626820 64
1795626825 60
1795626830 60
1795626835 60
1795626840 60
1795626845 60
1795626850 60
1795626855 60
1795626860 60
```
</details>

---

