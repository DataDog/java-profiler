---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-09 06:38:28 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (4 unique values: 63-96 cores)</summary>

```
1791541853 94
1791541858 94
1791541863 94
1791541868 94
1791541873 94
1791541878 96
1791541883 96
1791541888 96
1791541893 96
1791541898 96
1791541903 94
1791541908 94
1791541913 94
1791541918 94
1791541923 94
1791541928 94
1791541933 92
1791541938 92
1791541943 92
1791541948 92
```
</details>

---

