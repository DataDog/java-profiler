---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 06:16:25 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 75-96 cores)</summary>

```
1793355103 75
1793355108 75
1793355113 96
1793355118 96
1793355123 96
1793355128 96
1793355133 96
1793355138 96
1793355143 96
1793355149 96
1793355154 96
1793355159 96
1793355164 96
1793355169 96
1793355174 96
1793355179 96
1793355184 96
1793355189 96
1793355194 96
1793355199 96
```
</details>

---

