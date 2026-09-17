---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 589 |
| Sample Rate | 9.82/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (5 unique values: 78-86 cores)</summary>

```
1789682154 78
1789682159 78
1789682164 78
1789682169 80
1789682174 80
1789682179 80
1789682184 80
1789682189 80
1789682194 80
1789682199 80
1789682204 80
1789682209 80
1789682214 82
1789682219 82
1789682224 82
1789682229 82
1789682234 82
1789682239 82
1789682244 82
1789682249 82
```
</details>

---

