---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-23 08:55:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1792759858 15
1792759863 15
1792759868 15
1792759873 15
1792759878 15
1792759883 15
1792759888 15
1792759893 15
1792759898 15
1792759903 15
1792759908 15
1792759913 32
1792759918 32
1792759923 11
1792759928 11
1792759933 11
1792759938 11
1792759943 11
1792759948 11
1792759953 11
```
</details>

---

