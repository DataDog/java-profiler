---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-16 12:13:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1789574837 76
1789574842 76
1789574847 76
1789574852 74
1789574857 74
1789574862 74
1789574867 74
1789574872 74
1789574877 74
1789574882 74
1789574887 74
1789574892 74
1789574897 74
1789574902 74
1789574907 74
1789574912 74
1789574917 76
1789574922 76
1789574927 76
1789574932 76
```
</details>

---

