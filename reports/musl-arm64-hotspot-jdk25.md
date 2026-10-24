---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-24 04:44:32 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792831129 51
1792831134 64
1792831139 64
1792831144 64
1792831149 64
1792831154 64
1792831159 64
1792831164 64
1792831169 64
1792831174 64
1792831179 64
1792831184 64
1792831189 64
1792831194 64
1792831199 64
1792831204 64
1792831209 64
1792831214 64
1792831219 64
1792831224 64
```
</details>

---

