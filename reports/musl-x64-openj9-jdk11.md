---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 07:23:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 912 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 76-79 cores)</summary>

```
1793359129 79
1793359134 79
1793359139 78
1793359144 78
1793359149 78
1793359154 78
1793359159 78
1793359164 78
1793359169 78
1793359174 78
1793359179 78
1793359184 78
1793359189 78
1793359194 78
1793359199 78
1793359204 78
1793359209 78
1793359214 76
1793359219 76
1793359224 76
```
</details>

---

