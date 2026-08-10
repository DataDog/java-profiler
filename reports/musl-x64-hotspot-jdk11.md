---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 15:00:51 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (2 unique values: 86-91 cores)</summary>

```
1786388112 86
1786388117 86
1786388122 86
1786388127 86
1786388132 86
1786388137 86
1786388142 86
1786388147 86
1786388152 86
1786388157 86
1786388162 86
1786388167 86
1786388172 86
1786388177 86
1786388182 91
1786388187 91
1786388192 91
1786388197 91
1786388202 91
1786388207 91
```
</details>

---

