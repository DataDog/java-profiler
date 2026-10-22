---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 12:40:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1792686858 30
1792686863 30
1792686868 30
1792686873 30
1792686878 30
1792686883 30
1792686888 35
1792686893 35
1792686898 35
1792686903 35
1792686908 35
1792686913 35
1792686918 35
1792686923 35
1792686928 35
1792686933 35
1792686938 35
1792686943 35
1792686948 35
1792686953 35
```
</details>

---

