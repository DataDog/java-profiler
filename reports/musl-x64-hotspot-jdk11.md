---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 14:08:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 974 |
| Sample Rate | 16.23/sec |
| Health Score | 1014% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 35-39 cores)</summary>

```
1773252128 39
1773252133 39
1773252138 39
1773252143 39
1773252148 39
1773252153 39
1773252158 39
1773252163 39
1773252168 39
1773252173 39
1773252178 39
1773252183 35
1773252188 35
1773252193 35
1773252198 35
1773252203 35
1773252208 35
1773252213 35
1773252218 35
1773252223 35
```
</details>

---

