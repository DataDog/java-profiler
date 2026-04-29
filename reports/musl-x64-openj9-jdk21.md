---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:09:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 77-87 cores)</summary>

```
1777475099 77
1777475104 77
1777475109 81
1777475114 81
1777475119 81
1777475124 81
1777475129 81
1777475134 81
1777475139 83
1777475144 83
1777475149 83
1777475154 83
1777475159 83
1777475164 83
1777475169 83
1777475174 83
1777475179 83
1777475184 83
1777475189 83
1777475194 83
```
</details>

---

