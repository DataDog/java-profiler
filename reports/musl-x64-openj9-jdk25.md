---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-01 16:19:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 502 |
| Sample Rate | 8.37/sec |
| Health Score | 523% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 26-29 cores)</summary>

```
1790885686 26
1790885691 26
1790885696 26
1790885701 26
1790885706 26
1790885711 26
1790885716 26
1790885721 26
1790885726 26
1790885731 26
1790885736 26
1790885741 29
1790885746 29
1790885751 29
1790885756 29
1790885761 29
1790885766 29
1790885771 29
1790885776 29
1790885781 29
```
</details>

---

