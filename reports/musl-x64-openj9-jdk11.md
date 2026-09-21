---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 22-32 cores)</summary>

```
1789992186 22
1789992191 22
1789992196 22
1789992201 22
1789992206 22
1789992211 22
1789992216 22
1789992221 22
1789992226 22
1789992231 22
1789992236 22
1789992241 32
1789992246 32
1789992251 32
1789992256 32
1789992261 32
1789992266 32
1789992271 32
1789992276 32
1789992281 32
```
</details>

---

