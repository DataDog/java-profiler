---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 16:23:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 13 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1792441133 54
1792441138 54
1792441143 49
1792441148 49
1792441153 49
1792441158 49
1792441163 49
1792441168 49
1792441173 49
1792441178 49
1792441183 49
1792441188 49
1792441193 49
1792441198 49
1792441203 49
1792441208 49
1792441213 49
1792441218 54
1792441223 54
1792441228 54
```
</details>

---

