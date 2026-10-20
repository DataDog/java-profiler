---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 10:11:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1792505127 84
1792505132 84
1792505137 84
1792505142 84
1792505147 84
1792505152 84
1792505157 84
1792505162 86
1792505167 86
1792505172 86
1792505177 88
1792505182 88
1792505187 88
1792505192 88
1792505197 88
1792505202 88
1792505207 86
1792505212 86
1792505217 86
1792505222 86
```
</details>

---

