---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:56:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 120 |
| Sample Rate | 2.00/sec |
| Health Score | 125% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794750745 32
1794750750 32
1794750755 32
1794750760 32
1794750765 32
1794750770 32
1794750775 32
1794750780 32
1794750785 32
1794750790 32
1794750795 32
1794750800 32
1794750805 32
1794750810 32
1794750815 32
1794750821 32
1794750826 32
1794750831 32
1794750836 32
1794750841 32
```
</details>

---

