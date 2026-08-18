---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 15:28:24 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 11 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1787080938 34
1787080943 14
1787080948 14
1787080953 14
1787080958 14
1787080963 14
1787080968 14
1787080973 14
1787080978 14
1787080983 14
1787080988 14
1787080993 14
1787080998 14
1787081003 14
1787081008 14
1787081013 14
1787081018 14
1787081023 14
1787081028 14
1787081033 14
```
</details>

---

