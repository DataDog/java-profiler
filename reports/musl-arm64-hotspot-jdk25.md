---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-06 09:30:44 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 11 |
| Allocations | 118 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1791293022 43
1791293027 43
1791293032 43
1791293037 43
1791293042 43
1791293047 43
1791293052 43
1791293057 43
1791293062 43
1791293067 43
1791293072 43
1791293077 48
1791293082 48
1791293087 48
1791293092 48
1791293097 48
1791293102 43
1791293107 43
1791293112 43
1791293118 43
```
</details>

---

