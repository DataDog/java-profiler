---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 09:30:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1792157116 32
1792157121 32
1792157126 32
1792157131 32
1792157136 32
1792157141 32
1792157146 32
1792157151 32
1792157156 32
1792157161 32
1792157166 32
1792157171 32
1792157176 32
1792157181 32
1792157186 32
1792157191 32
1792157196 32
1792157201 32
1792157206 32
1792157211 32
```
</details>

---

