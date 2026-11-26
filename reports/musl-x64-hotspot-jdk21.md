---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 11:54:37 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 87-96 cores)</summary>

```
1795711826 87
1795711831 87
1795711836 87
1795711841 87
1795711846 87
1795711851 87
1795711856 87
1795711861 87
1795711866 87
1795711871 87
1795711876 87
1795711881 87
1795711886 87
1795711891 87
1795711896 87
1795711901 87
1795711906 87
1795711911 87
1795711916 96
1795711921 96
```
</details>

---

