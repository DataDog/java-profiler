---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 12:39:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 10 |
| Allocations | 132 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 34-40 cores)</summary>

```
1792686858 40
1792686863 40
1792686868 40
1792686873 40
1792686878 40
1792686883 40
1792686888 40
1792686893 40
1792686898 40
1792686903 40
1792686908 40
1792686913 34
1792686918 34
1792686923 34
1792686928 34
1792686933 34
1792686938 34
1792686943 34
1792686948 34
1792686953 34
```
</details>

---

