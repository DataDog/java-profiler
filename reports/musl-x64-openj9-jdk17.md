---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 11 |
| Allocations | 418 |

<details>
<summary>CPU Timeline (3 unique values: 32-37 cores)</summary>

```
1773252133 32
1773252138 32
1773252143 32
1773252148 32
1773252153 32
1773252158 32
1773252163 36
1773252168 36
1773252173 36
1773252178 36
1773252183 36
1773252188 36
1773252193 36
1773252198 37
1773252203 37
1773252208 37
1773252213 37
1773252218 37
1773252223 37
1773252228 37
```
</details>

---

