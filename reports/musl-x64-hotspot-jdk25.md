---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:55:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 11 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 13 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 56-61 cores)</summary>

```
1773165002 59
1773165007 59
1773165012 61
1773165017 61
1773165022 61
1773165027 61
1773165032 61
1773165037 61
1773165042 61
1773165047 61
1773165052 61
1773165057 61
1773165062 61
1773165067 61
1773165072 61
1773165077 61
1773165082 61
1773165087 61
1773165092 61
1773165097 61
```
</details>

---

