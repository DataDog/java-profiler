---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:26:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (3 unique values: 33-48 cores)</summary>

```
1789737676 48
1789737681 48
1789737686 45
1789737691 45
1789737696 45
1789737701 45
1789737706 45
1789737711 45
1789737716 45
1789737721 45
1789737726 45
1789737731 45
1789737736 45
1789737741 45
1789737746 45
1789737751 45
1789737756 45
1789737761 45
1789737766 45
1789737771 45
```
</details>

---

