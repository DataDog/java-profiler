---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 11:23:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 7 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 32-40 cores)</summary>

```
1786547896 32
1786547901 32
1786547906 32
1786547911 32
1786547916 32
1786547921 32
1786547926 32
1786547931 32
1786547936 32
1786547941 32
1786547946 32
1786547951 32
1786547956 32
1786547961 32
1786547966 32
1786547971 32
1786547976 32
1786547981 32
1786547986 32
1786547991 32
```
</details>

---

