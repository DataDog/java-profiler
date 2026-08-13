---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 06:03:05 EDT

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 9 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 14 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1786615122 18
1786615127 18
1786615132 18
1786615137 18
1786615142 18
1786615147 18
1786615152 18
1786615158 13
1786615163 13
1786615168 13
1786615173 13
1786615178 13
1786615183 13
1786615188 13
1786615193 13
1786615198 13
1786615203 13
1786615208 13
1786615213 13
1786615218 13
```
</details>

---

