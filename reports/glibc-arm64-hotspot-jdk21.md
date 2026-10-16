---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-16 01:04:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792126867 48
1792126872 48
1792126877 48
1792126882 48
1792126887 48
1792126892 48
1792126897 48
1792126902 48
1792126907 48
1792126912 48
1792126917 48
1792126922 48
1792126927 48
1792126932 48
1792126937 38
1792126942 38
1792126947 38
1792126952 38
1792126957 38
1792126962 38
```
</details>

---

