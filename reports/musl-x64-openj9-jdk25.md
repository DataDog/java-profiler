---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:58:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 68-96 cores)</summary>

```
1795452812 96
1795452817 96
1795452822 68
1795452827 68
1795452832 68
1795452837 68
1795452842 68
1795452847 68
1795452852 70
1795452858 70
1795452863 70
1795452868 70
1795452873 70
1795452878 70
1795452883 70
1795452888 70
1795452893 70
1795452898 70
1795452903 70
1795452908 70
```
</details>

---

