---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 07:23:33 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 72-96 cores)</summary>

```
1793359114 72
1793359119 72
1793359124 72
1793359129 72
1793359134 72
1793359139 72
1793359144 72
1793359149 75
1793359154 75
1793359159 96
1793359164 96
1793359169 75
1793359174 75
1793359179 75
1793359184 75
1793359189 75
1793359194 75
1793359199 75
1793359204 75
1793359210 75
```
</details>

---

