---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 06:45:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1790592096 20
1790592101 20
1790592106 20
1790592111 20
1790592116 20
1790592121 20
1790592126 20
1790592131 22
1790592136 22
1790592141 22
1790592146 22
1790592151 22
1790592156 22
1790592161 22
1790592166 22
1790592171 22
1790592176 22
1790592181 22
1790592186 22
1790592191 22
```
</details>

---

