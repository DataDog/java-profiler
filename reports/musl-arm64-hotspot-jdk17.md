---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-18 15:28:27 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 10 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 32-52 cores)</summary>

```
1787080923 32
1787080928 32
1787080933 32
1787080938 32
1787080943 32
1787080948 32
1787080953 32
1787080958 32
1787080963 32
1787080968 32
1787080973 32
1787080978 32
1787080983 32
1787080988 32
1787080993 32
1787080998 32
1787081003 32
1787081008 32
1787081014 32
1787081019 32
```
</details>

---

