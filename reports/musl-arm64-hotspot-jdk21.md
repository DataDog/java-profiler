---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 08:19:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795698862 42
1795698867 42
1795698872 42
1795698877 42
1795698882 42
1795698887 47
1795698892 47
1795698897 47
1795698902 47
1795698908 47
1795698913 47
1795698918 47
1795698923 47
1795698928 47
1795698933 47
1795698938 47
1795698943 47
1795698948 47
1795698953 47
1795698958 47
```
</details>

---

