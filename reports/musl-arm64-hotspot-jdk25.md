---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 06:16:24 EDT

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
| CPU Cores (start) | 13 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (4 unique values: 12-18 cores)</summary>

```
1793355113 13
1793355118 13
1793355123 13
1793355128 13
1793355133 13
1793355138 13
1793355143 13
1793355148 12
1793355153 12
1793355158 12
1793355163 12
1793355168 14
1793355173 14
1793355178 14
1793355183 14
1793355188 14
1793355193 14
1793355198 18
1793355203 18
1793355208 18
```
</details>

---

