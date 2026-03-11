---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-11 14:08:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1773252127 54
1773252132 54
1773252138 54
1773252143 54
1773252148 54
1773252153 54
1773252158 54
1773252163 54
1773252168 54
1773252173 54
1773252178 54
1773252183 54
1773252188 54
1773252193 49
1773252198 49
1773252203 49
1773252208 49
1773252213 49
1773252218 49
1773252223 49
```
</details>

---

