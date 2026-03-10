---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-10 13:55:48 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 60-88 cores)</summary>

```
1773165001 88
1773165006 88
1773165011 88
1773165016 88
1773165021 88
1773165026 88
1773165031 88
1773165036 88
1773165041 88
1773165046 88
1773165051 88
1773165056 88
1773165061 88
1773165066 88
1773165071 88
1773165076 88
1773165081 67
1773165086 67
1773165091 64
1773165096 64
```
</details>

---

