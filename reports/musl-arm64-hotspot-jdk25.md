---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-08 13:30:11 EDT

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1775668982 64
1775668987 64
1775668992 64
1775668997 64
1775669002 64
1775669007 64
1775669012 64
1775669017 64
1775669022 64
1775669027 64
1775669032 64
1775669037 64
1775669042 64
1775669047 64
1775669052 64
1775669057 64
1775669062 64
1775669067 64
1775669072 64
1775669077 64
```
</details>

---

