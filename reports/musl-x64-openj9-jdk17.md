---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-30 07:23:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 83-93 cores)</summary>

```
1793359114 83
1793359119 83
1793359124 93
1793359129 93
1793359134 93
1793359139 93
1793359144 93
1793359149 93
1793359154 93
1793359159 93
1793359164 93
1793359169 93
1793359174 93
1793359179 93
1793359184 93
1793359189 93
1793359194 85
1793359199 85
1793359205 85
1793359210 85
```
</details>

---

