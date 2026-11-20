---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 16:44:20 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 15 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1795210750 45
1795210755 45
1795210760 45
1795210765 45
1795210770 45
1795210775 45
1795210780 45
1795210785 45
1795210790 45
1795210795 45
1795210800 45
1795210805 45
1795210810 45
1795210815 45
1795210820 45
1795210825 45
1795210830 45
1795210835 45
1795210840 45
1795210845 45
```
</details>

---

