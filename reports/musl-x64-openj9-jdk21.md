---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-23 19:01:54 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1792796143 55
1792796148 55
1792796153 55
1792796158 55
1792796163 55
1792796168 57
1792796173 57
1792796178 57
1792796183 57
1792796188 57
1792796193 57
1792796198 57
1792796203 57
1792796208 59
1792796213 59
1792796219 57
1792796224 57
1792796229 57
1792796234 57
1792796239 59
```
</details>

---

