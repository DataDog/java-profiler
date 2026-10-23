---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 19:01:54 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 55-59 cores)</summary>

```
1792796138 55
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
1792796218 57
1792796223 57
1792796228 57
1792796233 57
```
</details>

---

