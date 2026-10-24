---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 04:44:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 9 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 12 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1792831129 13
1792831134 18
1792831139 18
1792831144 18
1792831149 18
1792831154 18
1792831159 18
1792831164 18
1792831169 18
1792831174 18
1792831179 18
1792831184 18
1792831189 18
1792831194 18
1792831199 18
1792831204 18
1792831209 18
1792831214 18
1792831219 18
1792831224 18
```
</details>

---

