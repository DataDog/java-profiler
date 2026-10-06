---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 05:37:39 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 18-24 cores)</summary>

```
1791279070 24
1791279075 24
1791279080 24
1791279085 24
1791279090 24
1791279095 24
1791279100 24
1791279105 18
1791279110 18
1791279115 18
1791279120 18
1791279125 18
1791279130 18
1791279135 18
1791279140 18
1791279145 19
1791279150 19
1791279155 19
1791279160 19
1791279165 19
```
</details>

---

