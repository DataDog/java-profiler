---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-16 01:04:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792126792 30
1792126797 30
1792126802 30
1792126807 30
1792126812 32
1792126817 32
1792126822 32
1792126827 32
1792126832 32
1792126837 32
1792126842 32
1792126847 32
1792126852 32
1792126857 32
1792126862 32
1792126867 32
1792126872 32
1792126877 32
1792126882 32
1792126887 32
```
</details>

---

